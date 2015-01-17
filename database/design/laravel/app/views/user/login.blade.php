@extends('layout')

@section('content')
    {{Form::open(array('url' => 'user/post_login'))}}
        <h3>Login</h3>
        <input type="text" name="name" placeholder="user name">
        <input type="password" name="password" placeholder="password">
        <input type="submit"  value="login">
    {{Form::close()}}
@stop
