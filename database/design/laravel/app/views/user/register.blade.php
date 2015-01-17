@extends('layout')

@section('content')
    {{Form::open(array('url' => 'user/post_register', 'class' => 'form-inline'))}}
        <h3>Register</h3>
        <input type="text" name="name" placeholder="user name" class="form-control" required autofocus>
        <input type="password" name="password" placeholder="password" class="form-control" required>
        <input type="submit"  value="register" class="btn btn-success">
    {{Form::close()}}
@stop
