@extends('layout')

@section('content')
<ul>
@foreach($answer as $question) 
    <li><a href="">{{$question->question->question}}</a></li>
@endforeach
</ul>
@stop
