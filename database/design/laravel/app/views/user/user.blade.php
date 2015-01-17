@extends('layout')

@section('content')
<h1>{{$user->name}}</h1>
@if ($my_follower)
    <button>取消关注</button>
@else
    <button>关注</button>
@endif
    @foreach ($questions as $question)
        <div>
            <h4>Q: {{$question->question}}</h4>
            <p>A: {{$question->answer->answer}}</p>
        </div>
    @endforeach
@stop
