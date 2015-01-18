<?php

class QuestionController extends BaseController {
    public function get_answers($id) {
        $question = Question::find($id);
        $answers = $question->answers;
        return Response::json($answers);
    }

    public function question($question_id) {
        $question = Question::find($question_id);
        return View::make('question/question')
            ->with('title', 'question')
            ->with('question', $question);
    }

    // add comment
    public function add_comment() {
        $answer_id = Input::get('answer_id');
        $answer = Answer::find($answer_id);
        if ($answer) {
            $comment = new Comment;
            $comment->user_id = Auth::id();
            $comment->answer_id = $answer_id;
            $comment->comment = Input::get('comment');
        }
    }

    // get comment
    public function get_comment() {
        $answer_id = Input::get('answer_id');
        $answer = Answer::find($answer_id);
    }
    public function get_login() {
        if (Auth::check()) {
            return Redirect::route('home');
        } else {
            return View::make('user/login')->with('title', 'login page');
        }
    }
}

