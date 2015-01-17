<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{{{$title}}}</title>
    <link rel="stylesheet" href="{{{URL::asset('css/bootstrap.min.css')}}}">
</head>
<body>
    <div class="container">
        @yield('content')
    </div>
    <script src="{{{URL::asset('js/jquery.min.js')}}}"></script>
    <script src="{{{URL::asset('js/bootstrap.min.js')}}}"></script>
</body>
</html>
