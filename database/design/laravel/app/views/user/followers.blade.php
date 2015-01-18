@extends('layout')

@section('content')
    <h3>My Followers:</h3>
    <ul>
        @foreach ($followers as $user)
            <li><a href="{{{route('user', $user->user_id)}}}">{{$user->name}}</a></li>
        @endforeach
    </ul>
@stop
