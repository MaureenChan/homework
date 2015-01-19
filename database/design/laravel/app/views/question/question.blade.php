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
    <a href="{{route('user', $question->answer_user_id)}}">{{$question->answerer->name}}</a> /
    <span class="date">{{$question->answer->answer_date}}</span>
</div>
<div class="comment">
    <h4>Comment:</h4>
    {{Form::open(array('url' => '/question/add_comment',  'method' => 'post',  'class' => 'form-inline'))}}
    <input type="hidden" name="answer_id" value="{{{$question->answer->answer_id}}}" >
    <input type="hidden" name="question_id" value="{{{$question->question_id}}}" >
    <input type="text" class="form-contorol" name="comment" placeholder="your comment">
    <input type="submit" class="btn btn-success">
    {{Form::close()}}
    @foreach ($question->answer->comments as $comment)
        <div class="comment-item">
            <p>
                {{$comment->comment}} ----
                <a href="{{route('user', $comment->commenter->user_id)}}">{{$comment->commenter->name}}</a> /
                <span class="date">{{$comment->comment_date}}</span> 
                @if (Auth::id() == $comment->commenter->user_id)
                ----
                <span><a href="{{route('remove_comment', $comment->id)}}">remove</a></span> </p>
                @endif
        </div>
    @endforeach
</div>
@stop
