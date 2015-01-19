<?php
class Answer extends Eloquent {
    protected $table = 'answer';
    protected $primaryKey = 'answer_id';
    public $timestamps = false;

    public function comments() {
        return $this->hasMany('Comment', 'answer_id')
            ->orderBy('comment_date', 'desc');
    }


}
