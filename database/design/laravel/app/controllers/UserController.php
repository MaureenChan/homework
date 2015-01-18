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
        if (Auth::check()) {
            if ($id == Auth::id()) {
                return Redirect::route('me');
            }
        }
        $questions = $user
            ->questions()
            ->whereNotNull('answer_id')
            ->get();

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

    public function answer() {
        $question = Question::find(Input::get('question_id'));
        var_dump($question);
        if ($question == null) {
            return -1;
        } else {
            $answer = new Answer;
            $answer->save();
            $question->answer_id = $answer->answer_id;
            var_dump($question->answer_id);
            $answer->answer = Input::get('answer');
            $question->save();
            $answer->save();
        }
        return Redirect::route('me');
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

    // get my followers
    public function followers() {
        $followers = Auth::user()->followers;
        return View::make('user/followers')
            ->with('title', 'my followers')
            ->with('followers', $followers);
    }

    //get my followings
    public function followings() {
        $followings = Auth::user()->followings;
        return View::make('user/followings')
            ->with('title', 'my followings')
            ->with('followings', $followings);
    }

    // add good
    public function add_good($answer_id) {
        $answer = Answer::find($answer_id);
        if ($answer) {
            $count = Good::where('answer_id', '=', $answer_id)
                ->where('user_id', '=', Auth::id())
                ->count();
            if ($count <= 0) {
                $good = new Good;
                $good->user_id = Auth::id();
                $good->answer_id = $answer_id;
                $good->save();
            }
            return 0;
        }
        else
            return -1;
    } 

    // remove good
    public function remove_good($answer_id) {
        $answer = Answer::find($answer_id);
        if ($answer) {
            $good = Good::where('user_id', '=', Auth::id())
                ->where('answer_id', '=', $answer_id)
                ->delete();
            return 0;
        }
        return -1;
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
        $password = Hash::make($raw_password);
        echo $password;

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
