@extends('layout')

@section('content')
    <ul>
        @foreach ($users as $user)
            <li><a href="{{{route('user', $user->user_id)}}}">{{$user->name}}</a></li>
        @endforeach
    </ul>
@stop
