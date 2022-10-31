// pages/home/home.js
const ecBLE = require('../../utils/ecBLE.js')
const util = require('../../utils/util.js')
Page({

  /**
   * 页面的初始数据
   */
  data: {
    date:'2022-10-18',
    time: '08:00:00',
    textRevData: ""
    //displayTime: '08:00'

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    const ctx = this
    //on disconnect
    ecBLE.onBLEConnectionStateChange(() => {
      ctx.showModal("提示", "设备断开连接")
    });
    var a = util.formatTime(new Date());
    this.setData({
      date: a.slice(0, 10),
      time: a.slice(11, 16)
    })
    wx.getConnectedBluetoothDevices({
      services: ['0000FFF2-0000-1000-8000-00805F9B34FB'],
      success (res) {
        console.log(res)
        if(res.devices.name != "GetUp")
        {
          wx.showModal({
            title: '提示',
            content: '未连接闹钟设备',
            showCancel: false,
            success (res) {
              if (res.confirm) {
                console.log('用户点击确定');
                this.toBLEConnectpage();
              }
            }
          })
        }
      }
    })
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {
    
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {
    const ctx = this
    //on disconnect
    ecBLE.onBLEConnectionStateChange(() => {
      ctx.showModal("提示", "设备断开连接")
    })
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  },
  bindDateChange: function (e) {
    //console.log('picker发送选择改变，携带值为', e.detail.value)
    this.setData({
      date: e.detail.value
    })
  },
  bindTimeChange: function (e) {
    //console.log('picker发送选择改变，携带值为', e.detail.value)
    this.setData({
      time: e.detail.value
    })
  },
  sendFistTime: function () {
    ecBLE.onBLECharacteristicValueChange((str) => {
      let data = str + "\r\n"
      console.log(data)
      this.setData({ textRevData: data })
    })
    var date = this.data.date;
    var time = this.data.time;
    var setTime = date +' ' + time+":00";
    var nowTime = +new Date();
    var inputTime = +new Date(setTime);
    var times = inputTime - nowTime;
    var bleSendTimes
    ecBLE.easySendData("CANCEL\n",false);
    if(times>0)
    {
      bleSendTimes = 'T'+ String(times)+'\n';
      console.log(bleSendTimes);
      ecBLE.easySendData(bleSendTimes,false);
    }
    else{
      times+=(24*60*60*1000);
      bleSendTimes = 'T'+ String(times)+'\n';
      console.log(bleSendTimes);
      ecBLE.easySendData(bleSendTimes,false);
    }
    
    //接收到蓝牙单片机回传数据，显示弹窗↓
    if(this.data.textRevData=="TimeSeted\n")
    {
      wx.showModal({
        title: '提示',
        content: '闹钟设置成功',
        showCancel: false
      })
    }
  },

  sendNextTime: function () {
    //如果设置第二个闹钟，这是计算第二个闹钟时间和第一个闹钟时间相差的时间，但是考虑到单片机那边的程序不好写，暂且不要这个功能了吧。
  },

  cancelCountdown: function () {
    //发送指令使蓝牙单片机停止定时器工作
    ecBLE.easySendData("CANCEL\n",false);
  },

  closeAlarm: function () {//当下床扫码之后，发送指令使电机停止运行
    wx.scanCode({
      onlyFromCamera: true,
      scanType: ['qrCode'],
      success (res) {
        console.log(res);
        if(res="CancelAlarm")
        {
          ecBLE.easySendData("CANCEL\n",false);
          console.log("OK");
        }
      }
    })
    ecBLE.easySendData("CANCEL\n",false);
  },

  toBLEConnectpage: function () {
    wx.navigateTo({
      url: '../index/index'
    })
  },

  toRemotepage: function () {
    
  }
})


/**
 * 通过控制蓝牙发送的字符串来向蓝牙单片机下达指令，对应指令如下：
 * "T282xx98\n"（中间xx表示数字）:开始倒计时执行敲打人的程序，数值为毫秒，单片机将会开启定时器在设定毫秒之后启动电机A，开始锤人。
 * "STOP\n":停止锤人
 * "HAMMER\n":开启旋风锤模式，可以用于捶背
 */
