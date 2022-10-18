// pages/device.js
const ecBLE = require('../../utils/ecBLE.js')

var isCheckScroll = true
var isCheckRevHex = false
var isCheckSendHex = false
var sendData = ""

Page({

  /**
   * 页面的初始数据
   */
  data: {
    textRevData: "",
    scrollIntoView: "scroll-view-bottom"
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    const ctx = this
    //on disconnect
    ecBLE.onBLEConnectionStateChange(() => {
      ctx.showModal("提示", "设备断开连接")
    })
    //receive data
    ecBLE.onBLECharacteristicValueChange((str, strHex) => {
      let data = ctx.data.textRevData + "[" + ctx.dateFormat("hh:mm:ss,S", new Date()) + "]:" + (isCheckRevHex ? strHex : str) + "\r\n"
      console.log(data)
      ctx.setData({ textRevData: data })
      if (isCheckScroll) ctx.setData({ scrollIntoView: "scroll-view-bottom" })//scroll to bottom
    })
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    ecBLE.onBLEConnectionStateChange(() => { })
    ecBLE.closeBLEConnection()
  },
  showModal(title, content) {
    wx.showModal({
      title: title,
      content: content,
      showCancel: false
    })
  },
  checkScroll(e) {
    if (e.detail.value.length) isCheckScroll = true
    else isCheckScroll = false
  },
  checkRevHex(e) {
    if (e.detail.value.length) isCheckRevHex = true
    else isCheckRevHex = false
  },
  checkSendHex(e) {
    if (e.detail.value.length) isCheckSendHex = true
    else isCheckSendHex = false
  },
  inputSendData(e) {
    sendData = e.detail.value
  },
  btClearTap(){
    this.setData({ textRevData: "" })
  },
  async btSendTap() {
    if (isCheckSendHex) {
      if (sendData.length % 2 != 0) {
        this.showModal("提示", "数据长度只能是双数")
        return
      }
      if (!new RegExp("^[0-9a-fA-F]*$").test(sendData)) {
        this.showModal("提示", "数据格式错误，只能是0-9,a-f,A-F")
        return
      }
    }
    await ecBLE.easySendData(sendData.replace(/\n/g,"\r\n"), isCheckSendHex)
  },
  dateFormat(fmt, date) {
    var o = {
      "M+": date.getMonth() + 1,                 //月份   
      "d+": date.getDate(),                    //日   
      "h+": date.getHours(),                   //小时   
      "m+": date.getMinutes(),                 //分   
      "s+": date.getSeconds(),                 //秒   
      "q+": Math.floor((date.getMonth() + 3) / 3), //季度   
      "S": date.getMilliseconds()             //毫秒   
    };
    if (/(y+)/.test(fmt))
      fmt = fmt.replace(RegExp.$1, (date.getFullYear() + "").substr(4 - RegExp.$1.length));
    for (var k in o)
      if (new RegExp("(" + k + ")").test(fmt)) {
        console.log(RegExp.$1.length)
        console.log(o[k])
        fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? ((o[k]) + "").padStart(3, "0") : (("00" + o[k]).substr(("" + o[k]).length)));
      }
    return fmt;
  }
})
