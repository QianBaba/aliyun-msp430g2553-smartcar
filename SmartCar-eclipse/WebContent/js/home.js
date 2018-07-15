//address=""搜索蓝牙//address=设备mac地址，自动配对给出mac地址的设备
function searchDevices(address) {
    //注册类
    var main = plus.android.runtimeMainActivity();
    var IntentFilter = plus.android.importClass('android.content.IntentFilter');
    var BluetoothAdapter = plus.android.importClass("android.bluetooth.BluetoothAdapter");
    var BluetoothDevice = plus.android.importClass("android.bluetooth.BluetoothDevice");
    var BAdapter = BluetoothAdapter.getDefaultAdapter();
    console.log("开始搜索设备");
    var filter = new IntentFilter();
    var bdevice = new BluetoothDevice();
    var on = null;
    var un = null;
    var vlist1 = document.getElementById('list1'); //注册容器用来显示未配对设备
    vlist1.innerHTML = ''; //清空容器
    var vlist2 = document.getElementById('list2'); //注册容器用来显示未配对设备
    vlist2.innerHTML = ''; //清空容器
    BAdapter.startDiscovery(); //开启搜索
    var receiver;
    receiver = plus.android.implements('io.dcloud.android.content.BroadcastReceiver', {
        onReceive: function(context, intent) { //实现onReceiver回调函数
            plus.android.importClass(intent); //通过intent实例引入intent类，方便以后的‘.’操作
            console.log(intent.getAction()); //获取action
            if(intent.getAction() == "android.bluetooth.adapter.action.DISCOVERY_FINISHED"){
                main.unregisterReceiver(receiver);//取消监听
                console.log("搜索结束")
            }else{
            BleDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            //判断是否配对
            if (BleDevice.getBondState() == bdevice.BOND_NONE) {
                console.log("未配对蓝牙设备：" + BleDevice.getName() + '    ' + BleDevice.getAddress());
                //参数如果跟取得的mac地址一样就配对
                if (address == BleDevice.getAddress()) {
                    if (BleDevice.createBond()) { //配对命令.createBond()
                        console.log("配对成功");
                        var li2 = document.createElement('li'); //注册
                        li2.setAttribute('id', BleDevice.getAddress()); //蓝牙mac地址
                        li2.setAttribute('onclick', 'connection(id)'); //注册click点击列表进行打印
                        li2.innerText = BleDevice.getName();
                        vlist2.appendChild(li2);
                    }

                } else {
                    if(BleDevice.getName() != on ){ //判断防止重复添加
	                    var li1 = document.createElement('li'); //注册
	                    li1.setAttribute('id', BleDevice.getAddress()); //小车蓝牙mac地址
	                    li1.setAttribute('onclick', 'searchDevices(id)'); //注册click点击列表进行配对
	                    on = BleDevice.getName();
	                    li1.innerText = on;
	                    vlist1.appendChild(li1);
                    }
                }
            } else {
                if(BleDevice.getName() != un ){ //判断防止重复添加
                console.log("已配对蓝牙设备：" + BleDevice.getName() + '    ' + BleDevice.getAddress());
                var li2 = document.createElement('li'); //注册
                li2.setAttribute('id', BleDevice.getAddress()); //蓝牙mac地址
                li2.setAttribute('onclick', 'connection(id)'); 
                un = BleDevice.getName();               
                li2.innerText = un;
                vlist2.appendChild(li2);}
            }}
        }
    });

    filter.addAction(bdevice.ACTION_FOUND);
    filter.addAction(BAdapter.ACTION_DISCOVERY_STARTED);
    filter.addAction(BAdapter.ACTION_DISCOVERY_FINISHED);
    filter.addAction(BAdapter.ACTION_STATE_CHANGED);

    main.registerReceiver(receiver, filter); //注册监听
}

var device = null,
    BAdapter = null,
    BluetoothAdapter = null,
    uuid = null,
    main = null,
    bluetoothSocket = null;

function connection(mac_address) {
    if (!mac_address) {
        alert('请选择蓝牙打印机');
        return;
    }
	
    main = plus.android.runtimeMainActivity();
    BluetoothAdapter = plus.android.importClass("android.bluetooth.BluetoothAdapter");
    UUID = plus.android.importClass("java.util.UUID");
    uuid = UUID.fromString("00001101-0000-1000-8000-00805f9B34FB");//00001101-0000-1000-8000-00805F9B34FB
    BAdapter = BluetoothAdapter.getDefaultAdapter();
    device = BAdapter.getRemoteDevice(mac_address);
    plus.android.importClass(device);
    bluetoothSocket = device.createInsecureRfcommSocketToServiceRecord(uuid);
    plus.android.importClass(bluetoothSocket);

    if (!bluetoothSocket.isConnected()) {
        console.log('检测到设备未连接，尝试连接....');
        bluetoothSocket.connect();
    }

    console.log('设备已连接');

    if (bluetoothSocket.isConnected()) {
        $(".left .l_start").attr('disabled','true');
        conn=true;
        console.log(conn);
    }
}
//**********************************************************

var switch_b=1;
var start_stop=1;
var conn=false;

var str_start='1';//send start
var start_back='';//receive start

var str_stop='0';//send stop
var stop_back='';//receive stop

var str_left='2';
var str_right='3';
var str_back='4';
var str_duoji_reset='5';
var str_duoji_rotate='6';
var str_colorled='7';
var str_xunji='8';
var timer_pic_upload;
//**********************************************************
$(document).on("pagecreate","#home_page",function(){
	$(".left .l_start").attr('disabled','false');
	$(".switch_blue").change(function(){
		switch_b++;
        if(switch_b%2==0){
        	console.log("on");
        	searchDevices("address");
        }
        else {
        	if (bluetoothSocket.isConnected()) {
        		device = null //这里关键
        		bluetoothSocket.close(); //必须关闭蓝牙连接
        		console.log("off");
        		conn=false;
        	}
        }
    });
    $(".left .l_start").click(function(){
    	start_stop++
    	if(conn==true){
    		if(start_stop%2==0){
	        	$(".left .l_start").css("background",'url(img/stop.png)');	
	        	$(".left .l_start").css("background-size",'cover');
	        	console.log(str_start);
		        start_back=blooth_send_receive(str_start);
		        if(start_back=='1'){
		        	console.log(start_back);
		        	$(".normal").css('background','green');
		        	$(".run").css('background','green');
		        	$(".stopped").css('background','white');
		        	$(".exception").css('background','white');
		        }
		        else {
		        	
		        	$(".normal").css('background','white');
		        	$(".run").css('background','white');
		        	$(".stopped").css('background','white');
		        	$(".exception").css('background','red');
		        }
	        }
	        else {
	        	$(".left .l_start").css("background","url(img/start.png)");
	        	$(".left .l_start").css("background-size",'cover');
	        	console.log(str_stop);
		        stop_back=blooth_send_receive(str_stop);
		        if(start_back=='0'){
		        	console.log(stop_back);
		        	$(".run").css('background','white');
		        	$(".stopped").css('background','green');
		        	$(".normal").css('background','green');
		        	$(".exception").css('background','white');
		        }
		        else {
		        	
		        	$(".normal").css('background','white');
		        	$(".run").css('background','white');
		        	$(".stopped").css('background','white');
		        	$(".exception").css('background','red');
		        }
	        }
    	}
    	else alert("连接异常");
    });
    $(".left .l_left").click(function(){
    	if(conn==true){
    		console.log(str_left);
    		var left_back=blooth_send_receive(str_left);
    		if(left_back!='2')	$(".exception").css('background','red');
    	}
    	else alert("连接异常");
    });
    $(".right .r_right").click(function(){
    	if(conn==true){
    		console.log(str_right);
    		var right_back=blooth_send_receive(str_right);
    		if(right_back!='3')	$(".exception").css('background','red');
    	}
    	else alert("连接异常");
    });
    $(".left .l_advance").click(function(){
    	if(conn==true){
    		console.log(str_start);
    		var advance_back=blooth_send_receive(str_start);
    		if(advance_back!='1')	$(".exception").css('background','red');
    	}
    	else alert("连接异常");
    });
    $(".right .r_back").click(function(){
    	if(conn==true){
    		console.log(str_back);
    		var back=blooth_send_receive(str_back);
    		if(back!='4')	$(".exception").css('background','red');
    	}
    	else alert("连接异常");
    });
    $(".rotate").click(function(){
    	if(conn==true){
    		console.log(str_duoji_rotate);
    		var rotate_back=blooth_send_receive(str_duoji_rotate);
    		if(rotate_back=='6'){
    			$(".camera_check").css('background','blue');
    		}
    	}
    	else alert("连接异常");
    });
    $(".reset").click(function(){
    	if(conn==true){
    		console.log(str_duoji_reset);
    		var reset_back=blooth_send_receive(str_duoji_reset);
    		if(reset_back!='5'){
    			$(".exception").css('background','red');
    		}
    	}
    	else alert("连接异常");
    });
    $(".color_led").click(function(){
    	if(conn==true){
    		console.log(str_colorled);
    		var led_back=blooth_send_receive(str_colorled);
    		if(led_back!='7'){
    			$(".exception").css('background','red');
    		}
    		else  $(".led_free").css('background','teal');
    	}
    	else alert("连接异常");
    });
    $(".xunji").click(function(){
    	if(conn==true){
    		console.log(str_xunji);
    		var xunji_back=blooth_send_receive(str_xunji);
    		if(xunji_back!='8'){
    			$(".exception").css('background','red');
    		}
    		else  $(".xunji_free").css('background','yellow');
    	}
    	else alert("连接异常");
    });
    $("#freemove").click(function(){
    	//if(conn==true){
    		$(".freemove").css('background','red');
    		timer_pic_upload=setInterval(function(){freeMove()},5000);
    	//}
    	//else alert("连接异常");
    });
    
});

function blooth_send_receive(c_send)
{
	var outputStream = bluetoothSocket.getOutputStream();
	plus.android.importClass(outputStream);
	var inputStream = bluetoothSocket.getInputStream();
	plus.android.importClass(inputStream);
	var bytes = plus.android.invoke(c_send, 'getBytes', 'utf-8');
    outputStream.write(bytes);
    outputStream.flush();
    var c_receive=String.fromCharCode(inputStream.read());
    
    return c_receive;
}
function freeMove(){
	console.log(new Date());
	context1.drawImage(video, 0, 0,300,180);
	on_click_upload_file();
}