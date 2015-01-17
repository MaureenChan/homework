@extends('layout')

@section('content')
    {{Form::open(array('url' => 'user/post_register'))}}
        <h3>register</h3>
        <input type="text" name="username" placeholder="user name">
        <input type="password" name="password" placeholder="password">
        <input type="submit"  value="register">
    {{Form::close()}}
@stop
