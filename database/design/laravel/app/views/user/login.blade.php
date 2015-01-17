@extends('layout')

@section('content')
    {{Form::open(array('url' => 'user/post_login', 'class' => 'form-inline'))}}
        <h3>Login</h3>
        <input type="text" name="name" placeholder="user name" class="form-control" required autofocus>
        <input type="password" name="password" placeholder="password" class="form-control" required>
        <input type="submit"  value="login" class="btn btn-success">
    {{Form::close()}}
@stop
