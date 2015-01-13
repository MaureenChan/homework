$(document).ready(function () {
  (function () {
    var html = '';
    var algos = ['fcfs', 'hrrn', 'spf', 'rr', 'preemptive_spf'];
    html = template('algos', {algos: algos});
    $('#content').html(html);
  })();
  // 获取表单中的参数
  //var count = $('#count').val();
  var count = 5;

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
  var createTr = function (cb, algo) {
    var tr = $('<tr></tr>')
               .attr({
                 'id': algo + 'tr-' + cb.name
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
                 $('<td></td>').html(cb.rtime)
               ).append(
                 $('<td></td>').html(cb.ftime)
               ).append(
                 $('<td></td>').html(cb.super)
               ).append(
                 $('<td></td>').html(cb.ttime).addClass('ttime')
               ).append(
                 $('<td></td>').html(cb.wtime).addClass('wtime')
               );
    return tr;
  }


  // 生成随机数据
  var cbs = createCB('process', count);
  // 生产定制数据
  var customCbs = createCB('process', 5, [3,6,4,5,2], [0,2,4,6,8]);
  console.log(customCbs);

  $('.action').click(function (e) {
    var algo = this.id.substr(4);
    // 绘制初始化进度条
    var $progress = $('#progress-' + algo);
    var $tbody = $('#table-cbs-' + algo + ' tbody');
    $('#table-cbs-' + algo).show();
    $progress.empty();
    $tbody.empty();
    var type = $('input[name="type"]:checked').val();
    console.log(type);
    if (type === 'sample') {
      // 复制定制数据
      var ownCbs = $.extend(true, [], customCbs);
    } else if (type === 'random') {
      // 复制随机数据
      var ownCbs = $.extend(true, [], cbs);
    }
    ownCbs.forEach(function (cb) {
      $progress.append(createProgressBar(algo + cb.name, cb.ntime));
      $tbody.append(createTr(cb, algo));
    });
    $tbody.append(
      $('<tr></tr>')
        .attr({
          'id': algo + '-last-tr'
        })
        .append(
          $('<td colspan="2">平均周转时间</td>')
        ).append(
          $('<td colspan="2"></td>')
        ).append(
          $('<td colspan="2">平均带权周转时间</td>')
        ).append(
          $('<td colspan="3"></td>')
        )
    );

    console.log(ownCbs);

    var freq = 300;
    if (algo === 'fcfs') {
      fcfs(ownCbs, freq);
    } else if (algo === 'rr') {
      rr(ownCbs, freq);
    } else if (algo === 'hrrn') {
      hrrn(ownCbs, freq);
    } else if (algo === 'spf') {
      spf(ownCbs, freq);
    } else if (algo === 'preemptive_spf') {
      preemptive_spf(ownCbs, freq);
    }
  });


  function PCB(i, ntime, atime) {
    var ret = {};
    ret.name = 'process' + i;   //进程名
    ret.super = 0;              //完成次序标记
    //需要运行时间
    if (ntime !== undefined) {
      ret.ntime = ntime;
    } else {
      ret.ntime = parseInt(Math.random() * 90 + 10); 
    }
    // 到达时间
    if (atime != undefined) {
      ret.atime = atime;
    } else {
      ret.atime = parseInt(Math.random() * 100); 
    }
    ret.stime = 0;  //开始时间
    ret.rtime = 0;  //执行时间
    ret.ftime = 0;  //完成时间
    ret.ttime = 0;  //周转时间
    ret.wtime = 0;  //带权周转时间
    //更新表中数据
    ret.update = function (algo) {
      $('#' + algo + this.name).css('width', this.rtime / this.ntime * 100 + '%');
      $('#' + algo + 'tr-' + this.name + ' td')[3].innerHTML = this.stime;
      $('#' + algo + 'tr-' + this.name + ' td')[4].innerHTML = this.rtime;
      $('#' + algo + 'tr-' + this.name + ' td')[5].innerHTML = this.ftime;
      $('#' + algo + 'tr-' + this.name + ' td')[6].innerHTML = this.super;
      $('#' + algo + 'tr-' + this.name + ' td')[7].innerHTML = this.ttime;
      $('#' + algo + 'tr-' + this.name + ' td')[8].innerHTML = this.wtime.toFixed(2);

      var avg_ttime = 0;    //平均周转时间
      var avg_wtime = 0;    //平均带权周转时间

      var ttimes = $('#table-cbs-' + algo + ' .ttime');
      var wtimes = $('#table-cbs-' + algo + ' .wtime');

      for (var i = 0; i < ttimes.length; i++) {
        avg_ttime += Number(ttimes[i].innerHTML);
        avg_wtime += Number(wtimes[i].innerHTML);
      }

      avg_ttime /= ttimes.length;
      avg_wtime /= wtimes.length;


      $('#' + algo + '-last-tr' + ' td')[1].innerHTML = avg_ttime.toFixed(2);
      $('#' + algo + '-last-tr' + ' td')[3].innerHTML = avg_wtime.toFixed(2);
    };
    return ret;
  }
  //生成一个pcb
  function createCB(type, count, ntime, atime) {
    var ret = [];
    var CB;
    if (type === 'process') {
      CB = PCB;
    }
    for (var i = 0; i < count; i++) {
      // 如果 ntime 和 atime 有值则使用它们的值
      if (ntime && atime) {
        ret.push(new CB(i, ntime[i], atime[i]));
        console.log(ntime);
        console.log(atime);
        console.log(ret);
      // 如果没有就使用随机值
      } else {
        ret.push(new CB(i));
      }
    }
    return ret;
};
});
// 按到达时间升序排序
function com_atime(value1, value2) {
  return value1.atime - value2.atime;
}
// 按需要时间升序排序
function com_ntime(value1, value2) {
  return value1.ntime - value2.ntime;
}
// 按剩余工作时间排序
function com_rtime(value1, value2) {
  a = value1.ntime - value1.rtime;
  b = value2.ntime - value2.rtime;
  if(a > b)
    return 1;
  else if (a < b) 
    return -1;
  else 
    return 0;
}
// 先来先服务算法
function fcfs(cbs, fre) {
  var running = null;   // 存储正在运行的pcb
  var ready = [];       // 就绪队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var i = 1;            // 控制完成次序
  cbs.sort(com_atime);  // 初始进程队列按照到达时间排序
  var interval = setInterval(function () {
    //如果达到到达时间，则插入到就绪队列中
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
        // 存在进程则把就绪队列按照到达时间排序
        // 先到达的则先执行
        ready.sort(com_atime);
        running = ready.shift();
        running.stime = step;
        running.update('fcfs');
      }
    } else {
      // 如果存在进行的进程的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update('fcfs');
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('fcfs');
        console.log(running);
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
// 非抢占的短进程优先
function spf(cbs, fre) {
  var running = null;       // 存储正在运行的pcb
  var ready = [];           // 就绪队列
  var finish = [];          // 完成队列
  var step = 0;             // 全局时间控制
  var i = 1;                // 控制完成次序
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
        running.update('spf');
      }
    } else {
      // 如果存在进行的进程的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update('spf');
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('spf');
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
// 抢占的短进程优先
function preemptive_spf (cbs, fre) {
  var running = null;           // 存储正在运行的pcb
  var ready = [];               // 就绪队列
  var finish = [];              // 完成队列
  var step = 0;                 // 全局时间控制
  var i = 1;                    // 控制完成次序
  cbs.sort(com_atime);          // 初始进程队列按照到达时间排序
  var interval = setInterval(function () {
    //如果到达开始时间就进入就绪队列
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if (cbs.length == 0)
          break;
      }
    }
    ready.sort(com_atime);
    // 判断就绪队列是否有进程
    if (ready.length == 0) {
      //没有进程则时间向前移
      step++;
    } else {
      // 存在进程则把就绪队列按照剩余需要时间排序
      // 短的进程则先执行
      ready.sort(com_rtime);
      running = ready.shift();
      // 判断是否执行过
      if(running.rtime) {
        running.update('preemptive_spf');
      } else {
        // 没有被执行过则需要初始化开始时间
        running.stime = step;
        running.update('preemptive_spf');
      }
      if (running.rtime != running.ntime) {
        // 每次执行完一次之后要判断是否有进程来抢占
        running.rtime++;
        running.update('preemptive_spf');
        ready.push(running);
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('preemptive_spf');
        finish.push(running);
      }
    }

  }, fre);
}
// 高响应比优先算法
function hrrn(cbs, fre) {
  var running = null;       // 存储正在运行的pcb
  var ready = [];           // 就绪队列
  var finish = [];          // 完成队列
  var step = 0;             // 全局时间控制
  var i = 0;                // 控制完成次序
  cbs.sort(com_atime);      // 初始进程队列按照到达时间排序
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
        running.update('hrrn');
      }
    } else {
      // 如果存在进行的进程的话，则判断是否执行完毕
      if (running.rtime != running.ntime) {
        // 没有执行完毕则继续执行
        running.rtime++;
        running.update('hrrn');
        step++;
      } else {
        // 完成了则计算完成时间，周转时间和带权周转时间
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('hrrn');
        finish.push(running);
        running = null;
      }
    }
  }, fre);
}
// 时间片算法
function rr(cbs, fre) {
  var running;          // 存储正在运行的pcb
  var ready = [];       // 就绪队列
  var finish = [];      // 完成队列
  var step = 0;         // 全局时间控制
  var i = 1;            // 控制完成次序
  var len;              // 存储就绪队列长度
  cbs.sort(com_atime);  // 初始进程队列按照到达时间排序
  var interval = setInterval(function () {
    //如果到达开始时间就进入就绪队列
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        running = cbs.shift();
        if(ready.length) {
          // 就绪队列不空则等到前面队列执行之后才执行
          running.stime = step + ready.length;
        } else {
          // 就绪队列为空则马上执行
          running.stime = step;
        }
        running.update('rr');
        ready.push(running);
        if(cbs.length == 0)
          break;
      }
    }
    len = ready.length;

    if(len){
      running = ready.shift();
      running.update('rr');
      // 运行完成
      if(running.rtime == running.ntime) {
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('rr');
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
