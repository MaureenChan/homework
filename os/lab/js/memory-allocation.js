$(document).ready(function () {
  before.finish = $.extend(true, [], before.ready);

  var html = '';
  before.title1 = 'initial jobs';
  before.title2 = 'initial free';
  html = template('row', before);

  for (var i = 0, length = before.ready.length; i < length; i++) {
    bf.bf(bf.ready[i]);
    wf.wf(wf.ready[i]);
    ff.ff(ff.ready[i]);
    nf.nf(nf.ready[i]);
  }

  bf.free.sort(com_add);
  wf.free.sort(com_add);
  ff.free.sort(com_add);
  nf.free.sort(com_add);

  bf.title1 = 'bf finish';
  bf.title2 = 'bf free';
  html += template('row', bf);

  wf.title1 = 'wf finish';
  wf.title2 = 'wf free';
  html += template('row', wf);

  ff.title1 = 'ff finish';
  ff.title2 = 'ff free';
  html += template('row', ff);

  nf.title1 = 'nf finish';
  nf.title2 = 'nf free';
  html += template('row', nf);

  $('#data').html(html);


});
