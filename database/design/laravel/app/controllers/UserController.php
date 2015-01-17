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

}
