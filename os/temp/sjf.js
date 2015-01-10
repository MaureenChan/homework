function com_ltime(value1, value2){
	var left_time = value1.ntime - value1.rtime;
	var right_time = value2.ntime - value2.rtime;
	if(left_time < right_time)
		return -1;
	else if (left_time > right_time)
		return 1;
	else
		return 0;
}

function check(){
	console.log("\n !!!! 当前正在运行的进程是:" + running_pcb.name);
	disp(running_pcb);
	console.log("\n ****当前就绪队列的状态为:\n");
	for(pr in ready){
		console.log(pr);
	}
}
function disp(pr){
	console.log("\n qname\tstate\tsuper\tatime\tndtime\truntime \n")
	console.log(pr.name+'\t'+pr.state +'\t'+pr.super +'\t'+pr.atime+'\t'+pr.ntime+'\t'+pr.rtime);
	console.log("\n");
}

function PCB(){
	this.name = 'Process' + i++;
	this.super = i;
	this.ntime = parseInt(Math.random() * 100 + i);
	this.atime = parseInt(Math.random() * 100 + i);
	this.state = 'W';
	this.rtime = 0;
}

function running(){
	(running_pcb.rtime)++;
	if(running_pcb.rtime == running_pcb.ntime){
		ready.shift();
	}
	else{
		running_pcb.state = 'W';
		ready.sort(com_ltime);
	}
		
}
var ready = new Array();
var create = new Array();
var time = 0;
var i = 0;

var process0 = new PCB();
create.push(process0);
var process1 = new PCB();
create.push(process1);
var process2 = new PCB();
create.push(process2);

create.sort(com_atime);
ready.sort(com_ltime);

var running_pcb;
ready.push(create.shift());
running_pcb = ready.shift();
time += running_pcb.atime;

while(create.length != 0){
	while(time < create[0].atime){
		time++;
		if(running_pcb->rtime == running_pcb.ntime){
			ready.shift();
			if(ready.length != 0){
				if(time > ready[0].atime)
					running_pcb = ready.shift();
			}
		}else{
			(running_pcb.rtime)++;
		}
	}
	ready.push(create.shift());
	ready.push(running_pcb);
	ready.sort(com_ltime);
}
