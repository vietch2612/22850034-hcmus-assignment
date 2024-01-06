export class RideService {
  bookRide(start: string, end: string): string {
    return `Trip: A new trip is booked from ${start} to ${end}`;
  }
}
