// pages/home/home.js
const ecBLE = require('../../utils/ecBLE.js')
Page({

  /**
   * 页面的初始数据
   */
  data: {
    date:'2022-10-18',
    time: '08:00'

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    const ctx = this
    //on disconnect
    ecBLE.onBLEConnectionStateChange(() => {
      ctx.showModal("提示", "设备断开连接")
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
  sendcountDown: function () {
    var date = this.data.date;
    var time = this.data.time;
    var setTime = date +' ' + time + ':00';
    var nowTime = +new Date();
    var inputTime = +new Date(setTime);
    var times = inputTime - nowTime;
    var bleSendTimes = 'T'+ times;
    if(times>0)
    {
      console.log(times);
    ecBLE.easySendData(times);
    }
    else{
      wx.showModal({
        title: '错误！',
        content: '设定时间异常！请重新设定时间！',
        success (res) {
          if (res.confirm) {
            console.log('用户点击确定')
          } else if (res.cancel) {
            console.log('用户点击取消')
          }
        }
      })
    }
  },
  tiaozhuan: function () {
    wx.navigateTo({
      url: '../index/index'
    })
  }
})