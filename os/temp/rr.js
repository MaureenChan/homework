function PCB(){
	this.name = 'Process' + i++;					//进程名
	this.super = i;									//优先级
	this.ntime = parseInt(Math.random() * 100 + i);	//需要运行的时间
	this.atime = parseInt(Math.random() * 100 + i);	//到达时间
	this.stime = 0;									//开始运行时间
	this.rtime = 0;									//已经运行时间
	this.ftime = 0;									//完成时间
}

//创建队列时根据时间排队
function com_atime(value1, value2){
	if(value1.atime < value2.atime)
		return -1;
	else if (value1.atime > value2.atime)
		return 1;
	else
		return 0;
}

//就绪队列时根据需要运行时间排队
function com_rp(value1, value2){
	a = (stamp - value1.atime) / value1.ntime;
	b = (stamp - value2.atime) / value2.ntime;
	if(a > b)
		return -1;
	else if (a < b)
		return 1;
	else
		return 0;
}

//创建对象
function create_PCB(){
	var process0 = new PCB();
	create.push(process0);
	var process1 = new PCB();
	create.push(process1);
	var process2 = new PCB();
	create.push(process2);
	var process3 = new PCB();
	create.push(process3);
	var process4 = new PCB();
	create.push(process4);
	var process5 = new PCB();
	create.push(process5);

	create.sort(com_atime);
	console.log("Initial list:")
	console.log(create);
}

//每完成一个进程输出一次
function disp(){
	console.log("round:" + j++);
	console.log("ready list:")
	console.log(ready);
	console.log("create list:")
	console.log(create);
	console.log("finish list:")
	console.log(finish);
}

var ready = new Array();	//ready queue
var create = new Array();	//create queue
var finish = new Array();	//finish queue
var r_pcb;	//running pcb
var i = 0;
var j = 0;
var stamp;
var CPUTIME = 10;
create_PCB();

while(create.length != 0){
	r_pcb = create.shift();
	r_pcb.rtime += CPUTIME;
	if(r_pcb.rtime >= r_pcb.ntime)
		finish.push(r_pcb);
	else
		create.push(r_pcb);

	disp();
}

