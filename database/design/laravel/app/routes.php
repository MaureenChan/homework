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
    Route::get('followers', array(
        'as' => 'followers',
        'uses' => 'UserController@followers'
    ));

    // get all my following
    Route::get('followings', array(
        'as' => 'followings',
        'uses' => 'UserController@followings'
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
