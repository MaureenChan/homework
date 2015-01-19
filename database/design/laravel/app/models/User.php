<?php

use Illuminate\Auth\UserTrait;
use Illuminate\Auth\UserInterface;
use Illuminate\Auth\Reminders\RemindableTrait;
use Illuminate\Auth\Reminders\RemindableInterface;

class User extends Eloquent implements UserInterface, RemindableInterface {

	use UserTrait, RemindableTrait;

	/**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'user';

	/**
	 * The attributes excluded from the model's JSON form.
	 *
	 * @var array
	 */
	protected $hidden = array('password', 'remember_token');

    protected $primaryKey = 'user_id';

    public $timestamps = false;
    
    public function questions() {
        return $this->hasMany('Question', 'answer_user_id', 'user_id');
    }
    public function my_questions() {
        return $this->hasMany('Question', 'ask_user_id', 'user_id');
    }

    public function is_following($id) {
        $count = Follow::where('user_id', '=', $this->user_id)
            ->where('follower', '=', $id)
            ->count();
        if ($count)
            return true;
        else
            return false;
    }

    public function is_good($answer_id) {
        $count = Good::where('user_id', '=', $this->user_id)
            ->where('answer_id', '=', $answer_id)
            ->count();
        if ($count)
            return true;
        else 
            return false;
    }

    public function answers() {
        return $this->belongsToMany('Answer', 'good');
    }

    public function followers() {
        return $this->belongsToMany('User', 'follow', 'user_id', 'follower');
    }

    public function followings() {
        return $this->belongsToMany('User', 'follow', 'follower', 'user_id');
    }
}
