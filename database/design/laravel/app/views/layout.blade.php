<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{{{$title}}}</title>
    <link rel="stylesheet" href="{{{URL::asset('css/bootstrap.min.css')}}}">
</head>
<body>
    <nav class="navbar navbar-default">
        <a class="navbar-brand" href="{{{URL::to('/')}}}">Q&A</a>
        <ul class="nav nav-pills pull-right">
        @if (Auth::check())
        <li><a href="{{{route('me')}}}">{{Auth::user()->name}}</a></li>
        <li><a href="{{{route('logout')}}}">logout</a></li>
        @else
        <li><a href="{{{route('login')}}}">login</a></li>
        </ul>
        @endif
    </nav>
    <div class="container">
        @yield('content')
    </div>
    <script src="{{{URL::asset('js/jquery.min.js')}}}"></script>
    <script src="{{{URL::asset('js/bootstrap.min.js')}}}"></script>
</body>
</html>
