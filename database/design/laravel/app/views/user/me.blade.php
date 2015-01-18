@extends('layout')

@section('content')
<h1>{{Auth::user()->name}}</h1>
    <h2>Questions to answer:</h2>
    @foreach ($questions_to_answer as $question)
        <div>
            <h4>Q: {{$question->question}}</h4>
        </div>
        {{Form::open(array('url' => '/answer', 'class' => 'form-inline'))}}
        <input type="hidden" name="question_id" value="{{{$question->question_id}}}">
        <input type="text" name="answer" class="form-control">
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

