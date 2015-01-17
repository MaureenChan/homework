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
        return Response::json($questions);
    }

    public function add_follower($id) {
        $user = User::find($id);
        if ($user == null) {
            return -1;
        } else {
            $follow = new Follow;
            $follow->user_id = $id;
            $follow->follower = 2;
            $follow->save();
            return 0;
        }
    }

    public function delete_follower($id) {
        $user = User::find($id);

        if ($user == null) {
            return -1;
        } else {
            $follow = Follow::where('user_id', '=', $id)->where('follower', '=', 2)->delete();
            return 0;
        }
    }

    public function my_follower() {
        $follower = Follow::where('user_id', '=', 71)->get();
        var_dump($follower);
        return Response::json($follower);
    }

    public function my_following() {
        $following = Follow::where('follower', '=', 45)->get();
        var_dump($following);
        return Response::json($following);
    }

    public function get_login() {
        if (Auth::check()) {
            return Redirect::route('home');
        } else {
            return View::make('user/login')->with('title', 'login page');
        }
    }

    public function post_login() {
        $rules = array(
            'name' => 'required|max:16|min:4',
            'password' => 'required|max:16|min:6'
        );
        $validation = Validator::make(Input::get(), $rules);
        if ($validation->fails()) {
            $msg = $validation->messages();
            return Response::json($msg);
        }

        $name = Input::get('name');
        $raw_password = Input::get('password');

        if (Auth::attempt(array(
            'name' => $name,
            'password' => $raw_password
        ))) {
            return Redirect::intended('/');
        } else {
            $msg = 'login error';
            return Response::json($msg);
        }
    }

    public function get_register() {
        if (Auth::check()) {
            return Redirect::route('home');
        } else {
            return View::make('user/register')->with('title', 'register page');
        }
    }

    public function post_register() {
        $rules = array(
            'name' => 'required|max:16|min:4',
            'password' => 'required|max:16|min:6'
        );
        $validation = Validator::make(Input::get(), $rules);
        if ($validation->fails()) {
            $msg = $validation->messages();
            return Response::json($msg);
        }

        $name = Input::get('name');
        $raw_password = Input::get('password');
        $password = Hash::make($raw_password);

        if (User::where('name', '=', $name)->count() > 0) {
            $msg = 'user exist';
            return Response::json($msg);
        }

        $user = new User;
        $user->name = $name;
        $user->password = $password;
        $user->save();
        Auth::login($user);
        return Redirect::intended('/');
    }

}
