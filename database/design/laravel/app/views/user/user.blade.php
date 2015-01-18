@extends('layout')

@section('content')
<h1>{{$user->name}}</h1>
@if ($is_following)
    <button id="unfollow" class="btn btn-danger">取消关注</button>
    <button id="follow" style="display:none" class="btn btn-success">关注</button>
@else
    <button id="unfollow" style="display:none" class="btn btn-danger">取消关注</button>
    <button id="follow" class="btn btn-success">关注</button>
@endif
    @foreach ($questions as $question)
        <div>
            <input type="hidden" value="{{{$question->answer->answer_id}}}">
            <h4>Q: {{$question->question}}</h4>
            <p>A: {{$question->answer->answer}}</p>
            @if (Auth::user()->is_good($question->answer->answer_id))
                <button class="ungood btn btn-danger">取消good</button>
            @else
                <button class="good btn btn-success">good</button>
            @endif
        </div>
        <hr>
    @endforeach
<div>
{{Form::open(array('url' => 'ask', 'method' => 'post', 'id' => 'form-ask'))}}
<input type="hidden" name="user_id" value="{{{$user->user_id}}}">
{{Form::text('question')}}
{{Form::submit('Submit')}}
{{Form::close()}}
</div>
@stop

@section('js')
<script>
$(function () {
    $('#follow').click(changeFollowStatus);
    $('#unfollow').click(changeFollowStatus);
    $('.good').click(changeGoodStatus);
    $('.ungood').click(changeGoodStatus);
    $('#form-ask').submit(function () {
        if (!isLogin) {
            location.href = '{{{route('login')}}}';
            return false;
        }
    });
    function changeFollowStatus() {
        var id = this.id;
        if (id === 'follow') {
            var url = '{{{route('follow', $user->user_id)}}}';
        } else if (id === 'unfollow'){
            var url = '{{{route('unfollow', $user->user_id)}}}';
        }
        console.log(url);
        $.get(url, function (res) {
            if (res == 0) {
                if (id == 'follow') {
                    $('#unfollow').show();
                    $('#follow').hide();
                } else {
                    $('#unfollow').hide();
                    $('#follow').show();
                }
            }
        });
    }
    function changeGoodStatus() {
        var id = this.id;
        var $this = $(this);
        var isGood = $this.hasClass('good');
        console.log(isGood);
        var answer_id = $(this).parent().find('input[type="hidden"]').val();
        console.log(answer_id);
        if (isGood) {
            var url = '/user/good/' + answer_id;
        } else {
            var url = '/user/ungood/' + answer_id;
        }
        console.log(url);
        $.get(url, function (res) {
            console.log('res', res);
            if (res == 0) {
                if (isGood) {
                    $this.removeClass('btn-success');
                    $this.removeClass('good');
                    $this.addClass('btn-danger');
                    $this.addClass('ungood');
                    $this.html('ungood');
                } else {
                    $this.removeClass('btn-danger');
                    $this.removeClass('ungood');
                    $this.addClass('btn-success');
                    $this.addClass('good');
                    $this.html('good');
                }
            }
        });
    }
});
</script>
@stop
