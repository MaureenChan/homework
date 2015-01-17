<?php

class UserController extends BaseController {

    public function all_user() {
        $users = User::all();
        return Response::json($users);
    }

    public function get_by_id($id) {
        $user = User::find($id);
        return Response::json($user);
    }

    public function get_questions($id) {
        $user = User::find($id);
        $questions = $user->questions;
        //$questions = User::find($id)->questions();
        //var_dump($questions);
        return Response::json($questions);
    }

    public function get_login() {
        if (Auth::check()) {
            return Redirect::route('home');
        } else {
            return View::make('user/login')->with('title', 'login page');
        }
    }

}
