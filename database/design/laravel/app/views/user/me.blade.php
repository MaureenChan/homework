@extends('layout')

@section('css')
<style>
.question-item {
    margin-bottom: 30px;
}
</style>
@stop

@section('content')
<h1>{{Auth::user()->name}}</h1>
<a href="{{route('followers')}}">followers({{count(Auth::user()->followers)}})</a> /
<a href="{{route('followings')}}">followings({{count(Auth::user()->followings)}})</a>
    <div class="row">
        <div class="col-lg-6">
            <h2>Questions to answer:</h2>
            <hr>
            @foreach ($questions_to_answer as $question)
                <div class="question-item">
                    <h4>Q: {{$question->question}} -- <a href="{{route('user', $question->asker->user_id)}}">{{$question->asker->name}}</a> </h4>
                </div>
                {{Form::open(array('url' => '/answer', 'class' => 'form-inline', 'id' => 'form-answer'))}}
                <input type="hidden" name="question_id" value="{{{$question->question_id}}}">
                <input type="text" name="answer" class="form-control" required placeholder="your answer">
                <input type="submit" class="btn btn-success">
                {{Form::close()}}
            @endforeach
        </div>
        <div class="col-lg-6">
            <h2>Questions answered:</h2>
            <hr>
            @foreach ($questions_answered as $question)
                <div class="question-item">
                    <h4>Q: {{$question->question}} -- <a href="{{route('user', $question->asker->user_id)}}">{{$question->asker->name}}</a> </h4>
                    <p>A: {{$question->answer->answer}}</p>
                </div>
            @endforeach
        </div>
    </div>

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
