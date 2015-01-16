function Memory(ready, free) {
  this.ready = [];
  this.free = [];
  //for (var i = 0; i < ready.length; i++) {
    //this.ready.push(ready[i]);
  //}
  //for (var j = 0; j < free.length; j++) {
    //this.free.push(free[j]);
  //}
  this.ready = $.extend(true, [], Object(ready));
  this.free = $.extend(true, [], Object(free));

  this.finish = [];
  this.SIZE = 10;

}


//按空闲区大小降序排序
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
};

//按空闲区大小降序排序
Memory.prototype.d_com_size = function (value1, value2) {
    a = value1.size;
    b = value2.size;
    if (a < b) {
      return 1;
    } else if (a > b) {
      return -1;
    } else {
      return 0;
    }
};

var ready = [], 
    free = [];
init(ready, free);
console.log('ready and free', ready, free);
var before = new Memory(ready, free),
    bf = new Memory(ready, free),
    wf = new Memory(ready, free),
    ff = new Memory(ready, free),
    nf = new Memory(ready, free);

function init() {
  var count = 5;
  //随机生成作业链和空闲区链
  for (var i = 0; i < count; i++) {
    ready.push(new JOB(i));
    free.push(new release());
  }
  console.log('ready', ready);
  console.log('free', free);
  //生成无重叠的空闲区链
  free.sort(com_add);
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
  })(free);

  //作业的结构
  function JOB(num) {
    var ret = {};
    ret.num = num;
    ret.need = parseInt(rand(0, 100) + num);
    ret.address = 0;
    ret.state = 'apply memory';
    return ret;
  }

  //空闲区的结构
  function release() {
    var ret = {};
    ret.address = parseInt(rand(0, 1000));
    ret.size = parseInt(rand(0, 100));
    return ret;
  }

  //随机函数
  function rand(min, max) {
    return Math.floor(min + Math.random() * (max - min));
  }
}

//按地址升序排序
function com_add (value1, value2) {
  a = value1.address;
  b = value2.address;
  if (a > b) {
    return 1;
  } else if (a < b) {
    return -1;
  } else {
    return 0;
  }
};

// 以下为具体算法实现

// 最佳适应算法
bf.bf = function (job) {
  var r_free;
  var len = this.free.length;
  // 空闲链按空闲链区大小升序排序
  this.free.sort(this.a_com_size);
  // 把空闲链表遍历一次
  while (len--) {
    r_free = this.free.shift();
    //如果首个空闲区大小不符合则跳过
    if (r_free.size < job.need) {
      this.free.push(r_free);
      continue;
    } else if (r_free.size == job.need) {
      //如果空闲区大小与作业需要大小吻合，则分配且跳出循环
      job.state = "Done";
      job.address = r_free.address;
      this.finish.push(job);
      break;
    } else {
      // 如果空闲区切割后剩下的不能够满足SIZE需要, 则不分配
      if (r_free.size - this.SIZE < job.need) {
        this.free.push(r_free);
        continue;
      } else {
        // 如果空闲区切割后剩下的能够满足SIZE需要, 则分配
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
  //遍历一遍没有找到合适的，则分配失败
  if (job.address == 0) {
    job.state = 'False! Too Big!';
    this.finish.push(job);
  }
};

// 最坏适应算法
wf.wf = function (job) {
  var r_free;
  var len = this.free.length;
  // 空闲链按空闲链区大小降序排序
  this.free.sort(this.d_com_size);
  // 把空闲链表遍历一次
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

// 首次适应算法
ff.ff = function (job) {
  var r_free;
  var len = this.free.length;
  this.free.sort(com_add);
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

// 循环适应算法
nf.nf = function (job) {
  var r_free;
  var len = this.free.length;
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

