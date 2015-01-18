@extends('layout')

@section('css')
<style>
.question {

}

.comment {
    margin-top: 50px;
}
.comment {
    margin-bottom: 20px;
}
</style>
@stop

@section('content')
<div>
    <h3>Q:{{$question->question}}</h3>
    <p class='question'>A:{{$question->answer->answer}}</p>
</div>
<div class="comment">
    <h4>Comment:</h4>
    @foreach ($question->answer->comments as $comment)
        <div class="comment-item">
            <p>
                {{$comment->comment}} ----
                <a href="{{route('user', $comment->commenter->user_id)}}">{{$comment->commenter->name}}</a> /
                <span class="date">{{$comment->comment_date}}</span>
            </p>
        </div>
    @endforeach
</div>
@stop
