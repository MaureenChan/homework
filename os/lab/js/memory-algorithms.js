function memory(count) {
  this.ready = [];
  this.free = [];
  this.finish = [];
  this.SIZE = 10;

  for (var i = 0; i < count; i++) {
    this.ready.push(new JOB(i));
    this.free.push(new release());
  }

  this.free.sort(this.com_add);

  console.log('before union', this.free);
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

  function JOB(num) {
    this.num = num;
    this.need = parseInt(rand(0, 100) + num);
    this.address = 0;
    this.state = 'apply memory';
  }
  function release() {
    this.address = parseInt(rand(0, 1000));
    this.size = parseInt(rand(0, 100));
  }
  function rand(min, max) {
    return Math.floor(min + Math.random() * (max - min));
  }
}
memory.prototype.com_add = function (value1, value2) {
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
memory.prototype.a_com_size = function (value, value2) {
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
var bf = new memory(5);
bf.run = function (job) {
  this.free.sort(this.a_com_size);
};
console.log(bf);
