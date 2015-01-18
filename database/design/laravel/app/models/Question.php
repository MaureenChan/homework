<?php

class Question extends Eloquent {
    protected $table = 'question';
    protected $primaryKey = 'question_id';
    public $timestamps = false;

    public function asker() {
        return $this->belongsTo('User', 'ask_user_id');
    }

    public function answer() {
        return $this->hasOne('Answer', 'answer_id', 'answer_id');
    }

}
