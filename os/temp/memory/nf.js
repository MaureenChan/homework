
function job(){
	this.num = i++;
	this.need =	parseInt(rand(0,100) + i);
	this.address = 0;
	this.state = 'apply memory';
}

function release(){
	this.address = parseInt(rand(0, 1000) + i);
	this.size = parseInt(rand(0, 100) + i);
}

function rand(min, max){
	return Math.floor(min + Math.random() * (max - min));
}

function com_add(value1, value2){
	a = value1.address;
	b = value2.address;
	if(a > b)
		return 1;
	else if(a < b)
		return -1;
	else 
		return 0;
}
var ready = new Array();
var free = new Array();
var finish = new Array();
var SIZE = 10;
var N = 15;
var i = 0;

for ( var k = 0; k < N; k++){
	ready.push(new job());
}


for ( var k = 0; k < N; k++){
	free.push(new release());
}
free.sort(com_add);
console.log(free);
function union(free){
	var temp = free.shift();
	while(temp.address <= free[0].address){
		//console.log("compare");
		//console.log(temp);
		//console.log(free);
		//console.log("before");
		//console.log(temp);
		if(temp.address + temp.size >= free[0].address + free[0].size){
			//console.log("shift");
			//console.log(free.shift())
			//console.log(free);
			free.shift();
			continue;
		}else if(temp.address + temp.size >= free[0].address){
			temp.size = free[0].address + free[0].size - temp.address;
			free.shift();
			//console.log("after");
			//console.log(temp);
			//console.log("shift");
			//console.log(free.shift())
			//console.log(free);
			continue;
		}else{
			//console.log("after");
			//console.log(temp);
			free.push(temp);
			//console.log(free);
		}
		temp = free.shift();
	}
	free.push(temp);
}
union(free);
console.log("ready:");
console.log(ready);
console.log("free:");
console.log(free);
console.log("finish");
console.log(finish);
nf();

console.log("ready:");
console.log(ready);
console.log("free:");
console.log(free);
console.log("finish");
console.log(finish);
function nf(){
	var r_job;
	var r_free;
	while(ready.length){
		r_job = ready.shift();
		var len = free.length;
		while(len--){
			console.log("compare:");
			console.log(r_job);
			console.log(free);
			r_free = free.shift();
			if(r_free.size < r_job.need){	//如果当前空闲区不够大，则下一个
				free.push(r_free);
				continue;
			}else if(r_free.size == r_job.need){
				r_job.state = "Done";
				r_job.address = r_free.address;
				finish.push(r_job);
				break;
			}else{
				if(r_free.size - SIZE < r_job.need){
					free.push(r_free);
					continue;	
				}else{
					r_job.state = "Done";
					r_job.address = r_free.address;
					r_free.address = r_free.address + r_job.need + 1;
					r_free.size = r_free.size - r_job.need;
					finish.push(r_job);
					free.push(r_free);
					break;
				}
			}
		}
		if(r_job.address == 0){
			r_job.state = 'False! Too Big!';
			finish.push(r_job);
		}
	}
}
