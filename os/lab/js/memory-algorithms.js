function Memory(count) {
  this.ready = [];
  this.free = [];
  this.finish = [];
  this.SIZE = 10;

  //随机生成作业链和空闲区链
  for (var i = 0; i < count; i++) {
    this.ready.push(new JOB(i));
    this.free.push(new release());
  }

  this.free.sort(this.com_add);

  console.log('before union', this.free);
  //生成无重叠的空闲区链
  (function (free) {
    var temp = free.shift();
    while (temp.address <= free[0].address) {
      if (temp.address + temp.size >= free[0].address + free[0].size) {
        free.shift();
        continue;
      } else if (temp.address + temp.size >= free[0].address) {
        temp.size = free[0].address + free[0].size - temp.address;
        free.shift();
        continue;
      } else {
        free.push(temp);
      }
      temp = free.shift();
    } 
    free.push(temp);
  })(this.free);
  console.log('after union', this.free);

  //作业的结构
  function JOB(num) {
    this.num = num;
    this.need = parseInt(rand(0, 100) + num);
    this.address = 0;
    this.state = 'apply memory';
  }
  //空闲区的结构
  function release() {
    this.address = parseInt(rand(0, 1000));
    this.size = parseInt(rand(0, 100));
  }
  //随机函数
  function rand(min, max) {
    return Math.floor(min + Math.random() * (max - min));
  }
}

//按地址升序排序
Memory.prototype.com_add = function (value1, value2) {
  a = value1.address;
  b = value2.address;
  if (a > b) {
    return 1;
  } else if (a < b) {
    return -1;
  } else {
    return 0;
  }
}
//按大小升序排序
Memory.prototype.a_com_size = function (value1, value2) {
    a = value1.size;
    b = value2.size;
    if (a > b) {
      return 1;
    } else if (a < b) {
      return -1;
    } else {
      return 0;
    }
}

// 以下为具体算法实现
// 最佳适应算法
Memory.prototype.bf = function (job) {
  var r_free;
  var len = this.free.length;
  this.free.sort(this.a_com_size);
  while (len--) {
    r_free = this.free.shift();
    if (r_free.size < job.need) {
      this.free.push(r_free);
      continue;
    } else if (r_free.size == job.need) {
      job.state = "Done";
      job.address = r_free.address;
      this.finish.push(job);
      break;
    } else {
      if (r_free.size - this.SIZE < job.need) {
        this.free.push(r_free);
        continue;
      } else {
        job.state = "Done";
        job.address = r_free.address;
        r_free.address = r_free.address + job.need + 1;
        r_free.size = r_free.size - job.need;
        this.finish.push(job);
        this.free.push(r_free);
        break;
      }
    }
  }
  if (job.address == 0) {
    job.state = 'False! Too Big!';
    this.finish.push(job);
  }
};

Memory.prototype.wf = function (job) {
}


var bf = new Memory(5);
//for (var i = 0; i < memory.ready.length; i++) {
  //memory.bf(memory.ready[i]);
  //console.log(memory);
//}

// 最坏适应算法
