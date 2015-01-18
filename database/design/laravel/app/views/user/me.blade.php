@extends('layout')

@section('content')
<h1>{{Auth::user()->name}}</h1>
    <h2>Questions to answer:</h2>
    @foreach ($questions_to_answer as $question)
        <div>
            <h4>Q: {{$question->question}} -- {{$question->asker->name}}</h4>
        </div>
        {{Form::open(array('url' => '/answer', 'class' => 'form-inline', 'id' => 'form-answer'))}}
        <input type="hidden" name="question_id" value="{{{$question->question_id}}}">
        <input type="text" name="answer" class="form-control" required>
        <input type="submit" class="btn btn-success">
        {{Form::close()}}
        <hr>
    @endforeach

    <h2>Questions answered:</h2>
    @foreach ($questions_answered as $question)
        <div>
            <h4>Q: {{$question->question}} -- {{$question->asker->name}}</h4>
            <p>A: {{$question->answer->answer}}</p>
        </div>
    @endforeach
@stop

@section('js')
<script>
$(function () {
    $('#form-answer').submit(function () {
        if (!isLogin) {
            location.href = '{{{route('login')}}}';
            return false;
        }
    });
});
</script>
@stop
