import { Component, ViewChild } from '@angular/core';

import { Slides, NavController } from 'ionic-angular';

@Component({
  selector: 'page-contact',
  templateUrl: 'contact.html'
})
export class ContactPage {
@ViewChild("mySlider") slider: Slides;

  constructor(public navCtrl: NavController) {

  }

  onSlideChanged(e) {
	let currentIndex = this.slider.getActiveIndex();
	console.log("You are on Slide ", (currentIndex+1));
  
  
  }

}
