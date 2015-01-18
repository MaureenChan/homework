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
            <h4>Q: {{$question->question}}</h4>
            <p>A: {{$question->answer->answer}}</p>
        </div>
    @endforeach
<div>
{{Form::open(array('url' => 'ask', 'method' => 'post'))}}
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
});
</script>
@stop
