<?php
class Comment extends Eloquent {
    protected $table = 'comment';
    protected $primaryKey = 'id';
    public $timestamps = false;

    public function commenter() {
        return $this->belongsTo('User', 'user_id');
    }

    public function get_answer_id() {
        return $this->belongsTo('Answer', 'answer_id','id');
    }

}
