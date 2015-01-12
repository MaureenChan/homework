$(document).ready(function () {
  (function () {
    var html = '';
    var algos = ['fcfs', 'hrrn', 'spf', 'rr', 'preemptive_spf'];
    html = template('algos', {algos: algos});
    $('#content').html(html);
  })();
  // 获取表单中的参数
  //var count = $('#count').val();
  var count = 6;

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

  var cbs = createCB('process', count);
  console.log('new cbs', cbs);

  $('.action').click(function (e) {
    var algo = this.id.substr(4);
    // 绘制初始化进度条
    var $progress = $('#progress-' + algo);
    var $tbody = $('#table-cbs-' + algo + ' tbody');
    $('#table-cbs-' + algo).show();
    $progress.empty();
    $tbody.empty();
    var ownCbs = $.extend(true, [], cbs);
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
          $('<td colspan="2"></td>')
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


  function PCB(i) {
    var ret = {};
    ret.name = 'process' + i;
    ret.super = 0;
    ret.ntime = parseInt(Math.random() * 90 + 10);
    ret.atime = parseInt(Math.random() * 100);
    ret.stime = 0;
    ret.rtime = 0;
    ret.ftime = 0;
    ret.ttime = 0;
    ret.wtime = 0;
    ret.update = function (algo) {
      $('#' + algo + this.name).css('width', this.rtime / this.ntime * 100 + '%');
      $('#' + algo + 'tr-' + this.name + ' td')[3].innerHTML = this.stime;
      $('#' + algo + 'tr-' + this.name + ' td')[4].innerHTML = this.ftime;
      $('#' + algo + 'tr-' + this.name + ' td')[5].innerHTML = this.super;
      $('#' + algo + 'tr-' + this.name + ' td')[6].innerHTML = this.ttime;
      $('#' + algo + 'tr-' + this.name + ' td')[7].innerHTML = this.wtime.toFixed(2);

      var avg_ttime = 0;
      var avg_wtime = 0;

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
  function createCB(type, count) {
    var ret = [];
    var CB;
    if (type === 'process') {
      CB = PCB;
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
function fcfs(cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
  var i = 1;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      ready.sort(com_atime);
      if (ready.length == 0){
        step++;
      } else if (step >= ready[0].atime) {
        running = ready.shift();
        running.stime = step;
        running.update('fcfs');
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update('fcfs');
        step++;
      } else {
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
function spf(cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
  var i = 1;
  cbs.sort(com_atime);
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
      ready.sort(com_ntime);
      if (ready.length == 0){
        step++;
      } else if (step >= ready[0].atime) {
        running = ready.shift();
        running.stime = step;
        running.update('spf');
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update('spf');
        step++;
      } else {
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
function preemptive_spf (cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
  var i = 1;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if (cbs.length == 0)
          break;
      }
    }
    console.log(ready);
    console.log(finish);
    if (ready.length == 0) {
      step++;
    } else {
      ready.sort(com_rtime);
      running = ready.shift();
      if(running.rtime) {
        running.update('preemptive_spf');
      } else {
        running.stime = step;
        running.update('preemptive_spf');
      }
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update('preemptive_spf');
        ready.push(running);
        step++;
      } else {
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
function hrrn(cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
  var i = 0;
  cbs.sort(com_atime);

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
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }

    if(running == null) {
      ready.sort(com_rp);
      if (ready.length == 0){
        step++;
      } else if (step >= ready[0].atime) {
        running = ready.shift();
        running.stime = step;
        running.update('hrrn');
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update('hrrn');
        step++;
      } else {
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
function rr(cbs, fre) {
  var ready = [];
  var running;
  var finish = [];
  var i = 1;
  var step = 0;
  var len;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        running = cbs.shift();
        if(ready.length) {
          running.stime = step + ready.length;
        } else {
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
      if(running.rtime == running.ntime) {
        running.ftime = step;
        running.ttime = running.ftime - running.atime;
        running.wtime = running.ttime / running.ntime;
        running.super = i++;
        running.update('rr');
        finish.push(running);
      } else {
        running.rtime++;
        step++;
        ready.push(running);
      }
    } else {
      step++;
    }

  }, fre);
}
