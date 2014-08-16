/***********************************************************************\
 * $NAME$ pins                                                         *
\***********************************************************************/

#if HAS_OUTPUT
inline void $NAME$_write( uint8_t v ) { $OUTREG$ = ($OUTREG$ & $CLEARMASK$) | $OUTPUT$; }
inline void $NAME$_set( uint8_t v )   { $OUTREG$ |=  $OUTPUT$; }
inline void $NAME$_clear( uint8_t v ) { $OUTREG$ &= ~$OUTPUT$; }
#endif // HAS_OUTPUT
#if HAS_INPUT
inline uint8_t $NAME$_read() { return $INPUT$; }
#endif // HAS_INPUT

