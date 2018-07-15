# aliyun-msp430g2553-smartcar
#硬件课设——基于阿里云图像识别和msp430g2553的智能小车

# 开发环境
后台（eclipse+java+mysql）：阿里云对象存储和图像识别API；
硬件（ccs6）：msp430g2553；
前端（HBuilder）:h5+jquery mobile

# 详细描述
1.硬件平台ccs6编写小车的控制程序

包括：蓝牙HC05+电机驱动tb6612fng+四路寻迹+红外避障+七彩灯+舵机旋转
下载至主控板msp430g2553

2.前端编写手机app页面

包括：蓝牙连接和开启手机摄像头+前后左右运动控制+摄像头采集+自动拍照和手动拍照+自动上传图片和手动上传+小车状态实时监测
h5软件：HBuilder

3.后台java+eclipse

实现用户登录，图片获取，图片上传至阿里云oss，图片通过oss url调用阿里云图像识别API得到识别结果发送至app,APP根据不同结果对小车做出不同响应

# 配置
1.SmartCar-client：前端开发的所有页面，可直接通过hbuilder打包到手机，hbuilder使用教程请自行搜索相应网站

2.SmartCar-eclipse：后台开发的整个eclipse工程，可直接导入到eclipse，请提前配置好java ee开发环境

3.SmartCar-ccs6：硬件平台开发的整个工程，可直接导入

# 代码修改
1.请将代码中服务器地址（hostname）修改为自己的服务器，位置在前端页面相应位置

2.请将阿里云的RAM访问ID和密码修改为自己的，位置在后台代码OSSClientConstants.java

3.请将mysql数据库修改为自己的，位置在后台代码DBMessage.java，请自己建立用户信息保存的数据库和表

使用时注意：请打开手机的自动旋转，否则页面会出现错乱，前端并不友好，master使用的是honor9调试的，若遇到其他问题请自己细心斟酌问题所在
