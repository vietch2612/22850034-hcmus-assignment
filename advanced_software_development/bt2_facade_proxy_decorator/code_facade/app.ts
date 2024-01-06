import { TaxiBookingFacade } from "./taxiBookingFacade";

// Usage
const bookingFacade = new TaxiBookingFacade();
const bookingDetails = bookingFacade.bookTaxi("Origin", "Destination", 25);
console.log(bookingDetails);
