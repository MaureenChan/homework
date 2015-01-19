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
    @if (Auth::id() == $question->answer_user_id)
        <a href="#" title="edit" id="edit" data-toggle="modal" data-target="#edit-modal"><span class="glyphicon glyphicon-edit"></span></a>
    @endif
</div>

<div class="modal fade" id="edit-modal">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title">edit your answer</h4>
            </div>
            <div class="modal-body">
                <form action="/update_answer" id="form-answer" method="post">
                    <textarea class="textarea form-control" name="answer" cols="30" rows="10">{{$question->answer->answer}}</textarea>
                    <input type="hidden" name="question_id" value="{{$question->question_id}}">
                    <input type="submit" class="btn btn-success form-control" value="save">
                </form>
            </div>
        </div>
    </div>
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

@section('js')
<script>
//$('#edit').click(function () {
    //return false;
//});
</script>
@stop
