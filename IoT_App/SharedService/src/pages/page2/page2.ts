import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { UserService } from '../../services/user';
import { Page1 } from '../page1/page1';


/*
  Generated class for the Page2 page.

  See http://ionicframework.com/docs/v2/components/#navigation for more info on
  Ionic pages and navigation.
*/
@Component({
  selector: 'page-page2',
  templateUrl: 'page2.html'
})

export class Page2 {

private user:any;
private nav: any;

  constructor(public navCtrl: NavController, user:UserService, nav:NavController) {
	console.log(user.name);
	this.user = user;
	this.nav = nav;
  }

  goToPage1(){
	this.nav.push(Page1);
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad Page2Page');
  }

}
