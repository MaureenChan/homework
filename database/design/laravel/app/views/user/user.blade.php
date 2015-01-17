@extends('layout')

@section('content')
<h1>{{$user->name}}</h1>
    <ul>
        @foreach ($questions as $question)
            <li><a href="/question/{{$question->question_id}}">{{$question->question}}</a></li>
        @endforeach
    </ul>
@stop
