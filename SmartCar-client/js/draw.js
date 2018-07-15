var canvas1 = document.getElementById("c1");
var canvas2 = document.getElementById("c2");
var ctx1 = canvas1.getContext("2d");
var ctx2 = canvas2.getContext("2d");
var ctx = null;
var offsetx = 10;
var offsety = 10;
var width = 270;
var height = 120;
var d = 1;

for (var c=1;c<=2;c++) {
	switch(c)
	{
		case 1:
		ctx=ctx1;
		break;
		case 2:
		ctx=ctx2;
		break;
	}
	ctx.fillStyle = "rgba(255,255,255,0)";
	ctx.fillRect (offsetx, offsety, width, height);

	for (var i = 0; i <= width/d; i++)
	{
	    if(i%20 == 0){
	         ctx.strokeStyle = "rgba(0,0,0,0.3)";
	         ctx.lineWidth = 1;
	    }else{
	         ctx.strokeStyle = "rgba(0,0,0,0)";
	    }
	    if(i==0){
	    	ctx.strokeStyle = "rgba(138,43,226,1)";
	    }
	    ctx.beginPath();
	    ctx.moveTo(i*d+offsetx,offsety);
	    ctx.lineTo(i*d+offsetx,height+offsety);
	    ctx.stroke();
	}
	
	/*绘制横行网格*/
	for (var j = 0; j <= height/d; j++)
	{
	    if (j%20 == 0){
	         ctx.strokeStyle = "rgba(0,0,0,0.3)";
	         ctx.lineWidth = 1;
	    }else{
	         ctx.strokeStyle = "rgba(0,0,0,0)";
	    }
	    if(j==60){
	    	ctx.strokeStyle = "rgba(138,43,226,1)";
	    }
	    ctx.beginPath();
	    ctx.moveTo(offsetx,j*d+offsety);
	    ctx.lineTo(width+offsetx,j*d+offsety);
	    ctx.stroke();
	}
	
	/*横纵坐标说明*/
	ctx.fillStyle = "rgb(0,0,0)";
	ctx.font="10px Arial";
	ctx.fillText("时间/t",width/2,130+offsety);
	
	switch(c){
		case 1:
		ctx.fillText("120",0,11);
		ctx.fillText("0",0,70);
		ctx.fillText("-120",0,140);
		ctx.fillText("135",offsetx+width*49/50,70);
		break;
		case 2:
		ctx.fillText("1.5",0,11);
		ctx.fillText("0",0,70);
		ctx.fillText("-1.5",0,140);
		ctx.fillText("135",offsetx+width*49/50,70);
		break;
	}
	
}