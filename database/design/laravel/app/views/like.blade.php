@extends('layout')

@section('content')
<ul>
@foreach($answer as $question) 
    <li><a href="{{route('question', $question->question->question_id)}}">{{$question->question->question}}</a></li>
@endforeach
</ul>
@stop
