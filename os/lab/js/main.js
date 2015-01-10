$(document).ready(function () {
  $('input[name="type"]').change(function() {
    var type = $('input[name="type"]:checked').val();
    console.log(type);
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
    console.log(type, algorithm, count);

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
    console.log('new cbs', cbs);

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
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    console.log('an interval');
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
      } else if (step < ready[0].atime){
        step++;
      } else if (step >= ready[0].atime) {
        running = ready.shift();
        running.stime = step;
        running.rtime++;
        console.log('rtime++');
        running.update();
        step++;
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update();
        step++;
      } else {
        running.ftime = step;
        running.update();
        finish.push(running);
        
        running = null;
        step++;
      }
    }
  }, fre);
}

function hrrn(cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var step = 0;
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
      } else if (step < ready[0].atime){
        step++;
      } else if (step >= ready[0].atime) {
        running = ready.shift();
        running.stime = step;
        running.rtime++;
        running.update();
        step++;
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update();
        step++;
      } else {
        running.ftime = step;
        running.update();
        finish.push(running);
        
        running = null;
        step++;
      }
    }
  }, fre);
}
function rr(cbs, fre) {
  var ready = [];
  var running;
  var finish = [];
  var step = 0;
  var len;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        running = cbs.shift();
        running.stime = step;
        running.update();
        ready.push(running);
        if(cbs.length == 0)
          break;
      }
    }
    len = ready.length;

    if(len){
      running = ready.shift();
      console.log(running);
      running.rtime++;
      running.update();
      if(running.rtime == running.ntime) {
        running.ftime = step;
        running.update();
        finish.push(running);
      } else {
        ready.push(running);
      }
    }
    step++;

  }, fre);
}

function fcfs(cbs, fre) {
  var running = null;
  var memory = 100;
  var tape = 5;
  var ready = [];
  var finish = [];
  var step = 0;
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
      } else if (step < ready[0].atime){
        step++;
      } else if (step >= ready[0].atime) {
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          if(memory >= running.mcount && tape >= running.tcount) {
            running.stime = step;
            running.rtime++;
            memory -= running.mcount;
            tape -= running.tcount;
            running.update();
            break;
          } else {
            ready.push(running);
          }
        }
        step++;
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
        running.update();
        step++;
      } else {
        running.ftime = step;
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        
        running = null;
        step++;
      }
    }
  }, fre);
}
function sjf(cbs, fre) {
  var running = null;
  var ready = [];
  var finish = [];
  var memory = 100;
  var tape = 5;
  var step = 0;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    console.log('an interval');
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
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          if(memory >= running.mcount && tape >= running.tcount) {
            running.stime = step;
            running.rtime++;
            console.log('rtime++');
            memory -= running.mcount;
            tape -= running.tcount;
            running.update();
            break;
          } else {
            ready.push(running);
          }
        }
        step++;
      }
    } else {
      if (running.rtime != running.ntime) {
        running.rtime++;
            console.log('rtime++');
        running.update();
        step++;
      } else {
        running.ftime = step;
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        
        running = null;
        step++;
      }
    }
  }, fre);
}
function pf(cbs, fre) {
  var running = null;
  var memory = 100;
  var tape = 5;
  var ready = [];
  var finish = [];
  var step = 0;
  cbs.sort(com_atime);
  var interval = setInterval(function () {
    if(cbs.length != 0) {
      while (step == cbs[0].atime) {
        ready.push(cbs.shift());
        if(cbs.length == 0)
          break;
      }
    }
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
      //console.log('running is null');
      ready.sort(com_super);
      if (ready.length == 0){
        //console.log('no ready');
        step++;
      } else if (step >= ready[0].atime) {
        //console.log('has ready');
        for(var i = 0; i < ready.length; i++){
          running = ready.shift();
          console.log(ready);
          if(memory >= running.mcount && tape >= running.tcount) {
            running.stime = step;
            console.log(running, 'start');
            running.rtime++;
            memory -= running.mcount;
            tape -= running.tcount;
            //console.log(running);
            running.update();
            break;
          } else {
            ready.push(running);
            running = null;
          }
        }
        step++;
      }
    } else {
      //console.log('continue running');
      if (running.rtime < running.ntime) {
        //console.log('not finish');
        running.rtime++;
        running.update();
        step++;
      } else {
        //console.log('finished');
        running.rtime++;
        running.ftime = step;
        memory += running.mcount;
        tape += running.tcount;
        running.update();
        finish.push(running);
        running = null;
        step++;
      }
    }
  }, fre);
}
