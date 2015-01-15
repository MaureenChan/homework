$(document).ready(function () {
  $('input[name="type"]').change(function() {
    var type = $('input[name="type"]:checked').val();
    var algorithms = $('#algorithm option');
    if (type === 'process') {
      $(algorithms[0]).val('HRRN');
      $(algorithms[1]).val('SPF');
      $(algorithms[2]).val('RR');

      $(algorithms[0]).text('HRRN');
      $(algorithms[1]).text('SPF');
      $(algorithms[2]).text('RR');
    } else if (type === 'job') {
      $(algorithms[0]).val('SJF');
      $(algorithms[1]).val('PF');
      $(algorithms[2]).val('FCFS');

      $(algorithms[0]).text('SJF');
      $(algorithms[1]).text('PF');
      $(algorithms[2]).text('FCFS');
    }
  });
  $('#form-args').submit(function() {
    // 获取表单中的参数
    var type = $('input[name="type"]:checked').val();
    var algorithm = $('#algorithm').val();
    var count = $('#count').val();

    // 创建一个进度条
    var createProgressBar = function (id, max) {
      var progressBar = $('<div></div>')
                           .addClass('progress')
                           .attr({
                             'style': 'width: ' + max * 10 + 'px'
                           })
                           .append(
                             $('<div></div>')
                               .addClass('progress-bar progress-bar-striped')
                               .attr({ 
                                 'role': 'progressbar',
                                 'aria-valuemin': 0, 
                                 'aria-valuemax': 100,
                                 'style': 'width: 0%',
                                 'id': id
                               })
                               .html(id)
                           );
      return progressBar;
    };
    // 创建一行数据
    var createTr = function (cb) {
      var tr = $('<tr></tr>')
                 .attr({
                   'id': 'tr-' + cb.name
                 })
                 .append(
                   $('<td></td>').html(cb.name)
                 ).append(
                   $('<td></td>').html(cb.atime)
                 ).append(
                   $('<td></td>').html(cb.ntime)
                 ).append(
                   $('<td></td>').html(cb.stime)
                 ).append(
                   $('<td></td>').html(cb.ftime)
                 ).append(
                   $('<td></td>').html(cb.super)
                 );
      return tr;
    }


    // 创建进程/作业数组
    if (type === 'process') {
      var cbs = createCB('process', count);
    } else if (type === 'job') {
      var cbs = createCB('job', count);
    }

    // 绘制初始化进度条
    var $progress = $('#progress');
    var $tbody = $('#table-cbs tbody');
    $progress.empty();
    $tbody.empty();
    cbs.forEach(function (cb) {
      $progress.append(createProgressBar(cb.name, cb.ntime));
      $tbody.append(createTr(cb));
    });

    var freq = 100;
    if (algorithm === 'HRRN') {
      hrrn(cbs, freq);
    } else if (algorithm === 'SPF') {
      spf(cbs, freq);
    } else if (algorithm === 'RR') {
      rr(cbs, freq);
    } else if (algorithm === 'SJF') {
      sjf(cbs, freq);
    } else if (algorithm === 'FCFS') {
      fcfs(cbs, freq);
    } else if (algorithm === 'PF') {
      pf(cbs, freq);
    }

    return false;
  })

  function PCB(i) {
    this.name = 'process' + i;
    this.super = i;
    this.ntime = parseInt(Math.random() * 90 + 10);
    this.atime = parseInt(Math.random() * 100);
    this.stime = 0;
    this.rtime = 0;
    this.ftime = 0;
  }
  function JCB(i) {
    this.name = 'job' + i;
    this.super = i;
    this.ntime = parseInt(Math.random() * 100);
    this.atime = parseInt(Math.random() * 100);
    this.stime = 0;
    this.rtime = 0;
    this.ftime = 0;
    this.mcount = parseInt(Math.random() * 100);
    this.tcount = parseInt(Math.random() * 4 + 1);
  }
  PCB.prototype.update = JCB.prototype.update = function () {
    $('#' + this.name).css('width', this.rtime / this.ntime * 100 + '%');
    $('#tr-' + this.name + ' td')[3].innerHTML = this.stime;
    $('#tr-' + this.name + ' td')[4].innerHTML = this.ftime;
  };
  function createCB(type, count) {
    var ret = [];
    var CB;
    if (type === 'process') {
      CB = PCB;
    } else if (type === 'job') {
      CB = JCB;
    }
    for (var i = 0; i < count; i++) {
      ret.push(new CB(i));
    }
    return ret;
  }
});
function com_atime(value1, value2) {
  return value1.atime - value2.atime;
}
function com_ntime(value1, value2) {
  return value1.ntime - value2.ntime;
}
function spf(cbs, fre) {
  var running = null;       // 存储正在运行的pcb
  var ready = [];           // 就绪队列
  var finish = [];          // 完成队列
  var step = 0;             // 全局时间控制
  cbs.sort(com_atime);      // 初始进程队列按照到达时间排序
  var interval = setInterval(function () {
    //如果到达开始时间就进入就绪队列
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      // 如果没有程序在运行,则判断就绪队列是否有进程
      if (ready.length == 0){
        //没有进程则时间向前移
        step++;
      } else if (step >= ready[0].atime) {
        // 存在进程则把就绪队列按照需要时间排序
        // 需要时间短的则先执行
        ready.sort(com_ntime);
        running = ready.shift();
        running.stime = step;
        running.update();
      }
    } else {
      // 如果存在进行的进程的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update();
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.update();
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
function hrrn(cbs, fre) {
  var running = null;   // 存储正在运行的pcb
  var ready = [];       // 就绪队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  cbs.sort(com_atime);  // 初始进程队列按照到达时间排序
  // 计算并优化响应比优先
  function com_rp(value1, value2) {
    a = (step - value1.atime) / value1.ntime;
    b = (step - value2.atime) / value2.ntime;
    if (a > b)
      return -1;
    else if (a < b)
      return 1;
    else 
      return 0;
  }
  var interval = setInterval(function () {
    //如果到达开始时间就进入就绪队列
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      // 如果没有程序在运行,则判断就绪队列是否有进程
      if (ready.length == 0){
        //没有进程则时间向前移
        step++;
      } else if (step >= ready[0].atime) {
        // 存在进程则把就绪队列按照响应比逆序排序
        // 响应比高的则先执行
        ready.sort(com_rp);
        running = ready.shift();
        running.stime = step;
        running.update();
      }
    } else {
      // 如果存在进行的进程的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update();
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.update();
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
function rr(cbs, fre) {
  var running;          // 存储正在运行的pcb
  var ready = [];       // 就绪队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var len;              // 存储就绪队列长度
  cbs.sort(com_atime);  // 初始进程队列按照到达时间排序
  var interval = setInterval(function () {
    //如果到达开始时间就进入就绪队列
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        running = cbs.shift();
        if (ready.length){
          // 就绪队列不空则等到前面队列执行之后才执行
          running.stime = step + ready.length;
        } else {
          // 就绪队列为空则马上执行
          running.stime = step;
        }
        running.update();
        ready.push(running);
        if(cbs.length == 0)
          break;
      }
    }
    len = ready.length;

    if(len){
      running = ready.shift();
      running.update();
      // 运行完成
      if(running.rtime == running.ntime) {
        running.ftime = step;
        running.update();
        finish.push(running);
      } else {
        // 还没运行完就运行一次后返回就绪队列
        running.rtime++;
        step++;
        ready.push(running);
      }
    } else {
      // 没有就绪队列就时间向前移
      step++;
    }

  }, fre);
}
function fcfs(cbs, fre) {
  var running = null;   // 存储正在运行的jcb
  var ready = [];       // 后备队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var memory = 100;     // 总共内存
  var tape = 5;         // 总磁带机数
  cbs.sort(com_atime);  // 初始作业队列按照到达时间排序
  var interval = setInterval(function () {
    //如果达到到达时间，则插入到后备队列中
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      // 如果没有程序在运行,则判断后备队列是否有作业
      if (ready.length == 0){
        //没有作业则时间向前移
        step++;
      } else if (step >= ready[0].atime) {
        // 存在则把后备队列按照到达时间排序
        // 先到达的并且资源需求得到满足则先执行
        ready.sort(com_atime);
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          if(memory >= running.mcount && tape >= running.tcount) {
            running.stime = step;
            // 分配资源
            memory -= running.mcount;
            tape -= running.tcount;
            running.update();
            break;
          } else {
            ready.push(running);
          }
        }
      }
    } else {
      // 如果存在进行的作业的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update();
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        // 回收资源
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
function sjf(cbs, fre) {
  var running = null;   // 存储正在运行的jcb
  var ready = [];       // 后备队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var memory = 100;     // 总共内存
  var tape = 5;         // 总磁带机数
  cbs.sort(com_atime);  // 初始作业队列按照到达时间排序
  var interval = setInterval(function () {
    //如果达到到达时间，则插入到后备队列中
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      // 如果没有程序在运行,则判断后备队列是否有作业
      if (ready.length == 0){
        //没有作业则时间向前移
        step++;
      } else if (step >= ready[0].atime) {
        ready.sort(com_ntime);
        // 存在则把后备队列按照要求服务时间排序
        // 再根据资源需求先得到满足则先执行
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          if(memory >= running.mcount && tape >= running.tcount) {
            // 分配资源
            running.stime = step;
            memory -= running.mcount;
            tape -= running.tcount;
            running.update();
            break;
          } else {
            ready.push(running);
          }
        }
      }
    } else {
      // 如果存在进行的作业的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update();
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        // 回收资源
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
function pf(cbs, fre) {
  var running = null;   // 存储正在运行的jcb
  var ready = [];       // 作业队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var memory = 100;     // 总共内存
  var tape = 5;         // 总磁带机数
  cbs.sort(com_atime);  // 初始作业队列按照到达时间排序
  var interval = setInterval(function () {
    //如果达到到达时间，则插入到后备队列中
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }
    // 按照优先级从高到低排序
    function com_super(value1, value2) {
      var a = value1.super;
      var b = value2.super;
      if (a < b)
        return -1;
      else if (a > b)
        return 1;
      else
        return 0;
    }

    if(running == null) {
      // 如果没有程序在运行,则判断后备队列是否有作业
      if (ready.length == 0){
        //没有作业则时间向前移
        step++;
      } else if (step >= ready[0].atime) {
        // 存在则把后备队列按照优先级排序
        // 先到达的并且资源需求得到满足则先执行
        ready.sort(com_super);
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          if(memory >= running.mcount && tape >= running.tcount) {
            running.stime = step;
            // 分配资源
            memory -= running.mcount;
            tape -= running.tcount;
            running.update();
            break;
          } else {
            ready.push(running);
            running = null;
          }
        }
      }
    } else {
      // 如果存在进行的作业的话，则判断是否执行完毕
      if (running.rtime < running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update();
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        // 回收资源
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
