@extends('layout')

@section('content')
<h1>{{Auth::user()->name}}</h1>
    <h2>Questions to answer:</h2>
    @foreach ($questions_to_answer as $question)
        <div>
            <h4>Q: {{$question->question}}</h4>
        </div>
        {{Form::open(array('url' => 'user/post_login', 'class' => 'form-inline'))}}
        <input type="text" class="form-control">
        <input type="submit" class="btn">
        {{Form::close()}}
        <hr>
    @endforeach

    <h2>Questions answered:</h2>
    @foreach ($questions_answered as $question)
        <div>
            <h4>Q: {{$question->question}}</h4>
            <p>A: {{$question->answer->answer}}</p>
        </div>
    @endforeach
@stop

