<?php
class Answer extends Eloquent {
    protected $table = 'answer';
    protected $primaryKey = 'answer_id';
    public $timestamps = false;

    public function comments() {
        return $this->hasMany('Comment', 'answer_id')
            ->orderBy('comment_date', 'desc');
    }

    public function question() {
        return $this->belongsTo('Question', 'answer_id', 'answer_id');
    }

    public function good() {
        return $this->hasMany('Good', 'answer_id', 'answer_id');
    }


    public function users() {
        return $this->belongsToMay('User', 'Good');
    }
}
