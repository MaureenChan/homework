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
function com_ntime(value1, value2){
	if(value1.ntime < value2.ntime)
		return -1;
	else if (value1.ntime > value2.ntime)
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

create_PCB();
while(finish.length != 3){	//判断是否全部进程都完成了
	if(finish.length == 0)	//完成队列为空，先来的马上运行
		ready.push(create.shift());
	else	//第一个完成之后判断时候有其它进程到达	
		while(create.length != 0 && stamp>= create[0].atime){	
			ready.push(create.shift());	//到达了就调入到就绪队列
			if(create.length == 0)
				break;
		}

	ready.sort(com_ntime);	//sort by their needed time;

	if(ready.length != 0){
		r_pcb = ready.shift();	//选择就绪队列的队首
		if(finish[finish.length-1]){	//如果在上一进程完成前已到达，则开始时间为上一进程完成时间
			if(finish[finish.length-1].ftime > r_pcb.atime){
				r_pcb.stime = finish[finish.length-1].ftime;	
			}else{	//如果在上一进程完成后没有进程到达，则开始时间为此进程的到达时间
				r_pcb.stime = r_pcb.atime;
			}
		}else{	//第一个进程专利
			r_pcb.stime = r_pcb.atime;
		}	
		r_pcb.rtime = r_pcb.ntime;
		r_pcb.ftime = r_pcb.stime + r_pcb.rtime;
		finish.push(r_pcb);
		stamp = r_pcb.ftime;
	}else{
		stamp = create[0].atime;
	}
	
	disp();
}

