<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the Closure to execute when that URI is requested.
|
*/

Route::get('/', array(
    'as' => 'home',
    'uses' => 'UserController@me'
));


// login stuff
Route::get('/user/register', array(
    'as' => 'register',
    'uses' => 'UserController@get_register'
));
Route::post('/user/post_register', array(
    'as' => 'post_register',
    'uses' => 'UserController@post_register'
));
Route::get('/user/login', array(
    'as' => 'login',
    'uses' => 'UserController@get_login'
));
Route::post('/user/post_login', array(
    'as' => 'post_login',
    'uses' => 'UserController@post_login'
));

// get all users
Route::get('/users/all', array(
    'as' => 'users',
    'uses' => 'UserController@all_user'
));

Route::group(array('before' => 'my_auth'), function() {
    Route::get('/me', array(
        'as' => 'me',
        'uses' => 'UserController@me'
    ));
    // get all my follower
    Route::get('/user/my_follower', array(
        'as' => 'followers',
        'uses' => 'UserController@my_follower'
    ));

    // get all my following
    Route::get('/user/my_following', array(
        'as' => 'followings',
        'uses' => 'UserController@my_following'
    ));

    // add follower
    Route::get('/user/follow/{user_id}', array(
        'as' => 'follow',
        'uses' => 'UserController@follow'
    ));

    // delete follower
    Route::get('/user/unfollow/{user_id}', array(
        'as' => 'unfollow',
        'uses' => 'UserController@unfollow'
    ));

    // add good
    Route::get('/user/good/{answer_id}', array(
        'as' => 'good',
        'uses' => 'UserController@add_good'
    ));

    // remove good
    Route::get('/user/ungood/{answer_id}', array(
        'as' => 'ungood',
        'uses' => 'UserController@remove_good'
    ));

    // add comment
    Route::post('/user/add_comment', array(
        'as' => 'add_comment',
        'uses' => 'UserController@add_comment'
    ));

    // get comment
    Route::get('/user/comment', array(
        'as' => 'comment',
        'users' => 'UserController@get_comment'
    ));

    // get my question
    Route::get('/user/{user_id}/questions', array(
        'as' => 'question',
        'uses' => 'UserController@get_questions'
    ));

    // ask question
    Route::post('/ask', array(
        'as' => 'ask',
        'uses' => 'UserController@ask'
    ));

    Route::get('/logout', array('as' => 'logout', function(){
        Auth::logout();
        return Redirect::route('login');
    }));

    Route::post('/answer', array(
        'as' => 'answer',
        'uses' => 'UserController@answer'
    ));

});

Route::filter('my_auth', function () {
    if (!Auth::check()) {
        return Redirect::route('login');
    }
});

// get user by id
Route::get('/user/{user_id}', array(
    'as' => 'user',
    'uses' => 'UserController@get_by_id'
));
