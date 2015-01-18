<?php

class UserController extends BaseController {

    // get all user, home page
    public function all_user() {
        $users = User::all();
        return View::make('user/all_users')
            ->with('title', 'login page')
            ->with('users', $users);
    }

    // user page
    public function get_by_id($id) {
        $user = User::find($id);
        $questions = $this->get_questions($id);

        return View::make('user/user')
            ->with('title', $user->name)
            ->with('user', $user)
            ->with('is_following', $user->is_following(Auth::id()))
            ->with('questions', $questions);
    }

    public function me() {
        $me = Auth::user();
        $questions_to_answer = $me
            ->questions()
            ->whereNull('answer_id')
            ->get();
        $questions_answered = $me
            ->questions()
            ->whereNotNull('answer_id')
            ->get();
        return View::make('user/me')
            ->with('title', Auth::user()->name)
            ->with('questions_to_answer', $questions_to_answer)
            ->with('questions_answered', $questions_answered);
    }

    public function ask() {
        $user = User::find(Input::get('user_id'));
        if ($user == null) {
            return -1;
        } else {
            $question = new Question;
            $question->question = Input::get('question');
            if ($question->question) {
                $question->ask_user_id = Auth::id();
                $question->answer_user_id = $user->user_id;
                $question->save();
            } else {
                var_dump("Question can't be empty");
            }
            return Redirect::route('user', $user->user_id);
        }
    }


    // follow someone
    public function follow($id) {
        $user = User::find($id);
        if ($user == null) {
            return -1;
        } else {
            $count = Follow::where('user_id', '=', $id)
                ->where('follower', '=', Auth::id())
                ->count();

            if ($count <= 0) {
                $follow = new Follow;
                $follow->user_id = $id;
                $follow->follower = Auth::id();
                $follow->save();
            }
            return 0;
        }
    }

    // unfollow someone
    public function unfollow($id) {
        $user = User::find($id);

        if ($user == null) {
            return -1;
        } else {
            $follow = Follow::where('user_id', '=', $id)->where('follower', '=', Auth::id())->delete();
            return 0;
        }
    }

    // get my follower
    public function my_follower() {
        $follower = Follow::where('user_id', '=', Auth::id())->get();
        return Response::json($follower);
    }

    //get my following
    public function my_following() {
        $following = Follow::where('follower', '=', Auth::id())->get();
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

    // get user question which has an answer
    private function get_questions($id) {
        $user = User::find($id);
        $questions = $user->questions()
            ->whereNotNull('answer_id')
            ->get();

        var_dump($questions);
        return $questions;
    }
}
