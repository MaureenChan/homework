@extends('layout')

@section('content')
    <h3>My Followings:</h3>
    <ul>
        @foreach ($followings as $user)
            <li><a href="{{{route('user', $user->user_id)}}}">{{$user->name}}</a></li>
        @endforeach
    </ul>
@stop
