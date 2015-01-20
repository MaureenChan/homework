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
        $question_id = Input::get('question_id');
        $answer = Answer::find($answer_id);
        if ($answer) {
            $comment = new Comment;
            $comment->user_id = Auth::id();
            $comment->answer_id = $answer_id;
            $comment->comment = Input::get('comment');
            $comment->comment_date = new DateTime();
            $comment->save();
            return Redirect::route('question/', $question_id);
        }
    }

    public function remove_comment($comment_id) {
        $comment = Comment::find($comment_id);
        if ($comment) {
            $answer_id = $comment->answer_id;
            $answer = Answer::find($answer_id);
            $question = $answer->question;
            $question_id = $question->question_id;
            $comment->delete();
            return Redirect::route('question', $question_id);
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

